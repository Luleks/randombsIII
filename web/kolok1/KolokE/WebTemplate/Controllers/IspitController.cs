namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class IspitController : ControllerBase
{
    public IspitContext Context { get; set; }

    public IspitController(IspitContext context)
    {
        Context = context;
    }

    [HttpPost("DodajGrad")]
    public async Task<ActionResult> DodajGrad([FromBody]Grad grad) {
        try {
            await Context.Gradovi.AddAsync(grad);
            await Context.SaveChangesAsync();
            return Ok($"Dodat grad sa id={grad.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajVoz")]
    public async Task<ActionResult> DodajVoz([FromBody]Voz voz) {
        try {
            await Context.Vozovi.AddAsync(voz);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat voz sa id={voz.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajRelaciju/{gradPolaskaID}/{gradDolaskaID}/{vozID}")]
    public async Task<ActionResult> DodajRelaciju(int gradPolaskaID, int gradDolaskaID, int vozID, [FromBody]Relacija rel) {
        try {
            var gradP = await Context.Gradovi.FindAsync(gradPolaskaID);
            var gradD = await Context.Gradovi.FindAsync(gradDolaskaID);
            var voz = await Context.Vozovi.FindAsync(vozID);
            if (gradP == null || gradD == null || voz == null)
                return NotFound("Nesto nije pronadjeno");
            if (voz.KapcitetPutnika < rel.BrPutnika)
                return StatusCode(StatusCodes.Status403Forbidden, "Previse putnika na relaciji");
            rel.PolazniGrad = gradP;
            rel.DolazniGrad = gradD;
            rel.Voz = voz;
            await Context.Relacije.AddAsync(rel);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata relacija sa id={rel.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PronadjiVozove/{gradID}")]
    public async Task<ActionResult> NadjiVozove(int gradID) {
        try {
            var vozovi = await Context.Relacije.Include(p => p.PolazniGrad)
                                               .Include(p => p.DolazniGrad)
                                               .Include(p => p.Voz)
                                               .Where(p => p.PolazniGrad!.ID == gradID || p.DolazniGrad!.ID == gradID)
                                               .Select(p => p.Voz)
                                               .ToListAsync();
            return Ok(vozovi);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("ZaradaVozaNaRel/{vozID}/{relID}")]
    public async Task<ActionResult> ZaradaVozaNaRelaciji(int relID, int vozID) {
        try {
            var relacija = await Context.Relacije.Include(p => p.PolazniGrad)
                                                 .Include(p => p.DolazniGrad)
                                                 .Where(p => p.ID == relID)
                                                 .Select(p => new {
                                                    PolazniGrad=p.PolazniGrad!.ID,
                                                    DolazniGrad=p.DolazniGrad!.ID
                                                 }).FirstOrDefaultAsync();
            if (relacija == null)
                return NotFound("Nije pronadjena relacija");
            var zarada = await Context.Relacije.Include(p => p.PolazniGrad)
                                               .Include(p => p.DolazniGrad)
                                               .Include(p => p.Voz)
                                               .Where(p => p.PolazniGrad!.ID == relacija.PolazniGrad &&
                                                           p.DolazniGrad!.ID == relacija.DolazniGrad ||
                                                           p.PolazniGrad!.ID == relacija.DolazniGrad &&
                                                           p.DolazniGrad!.ID == relacija.PolazniGrad &&
                                                           p.Voz!.ID == vozID)
                                                .SumAsync(p => p.CenaKarte * p.BrPutnika);
            return Ok(zarada);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    
}
