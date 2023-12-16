namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class IspitController : ControllerBase
{
    public Context Context { get; set; }

    public IspitController(Context context)
    {
        Context = context;
    }

    [HttpPost("DodajElektrodistribuciju")]
    public async Task<ActionResult> DodajElDistro([FromBody]Elektrodistribucija ed) {
        try {
            await Context.Elektrodistribucije.AddAsync(ed);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata elektrodistro sa id={ed.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajPotrosaca")]
    public async Task<ActionResult> DodajPotrosaca([FromBody]Potrosac potrosac) {
        try {
            await Context.Potrosaci.AddAsync(potrosac);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat potrosac sa id={potrosac.ID}");

        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajPotrosnju/{edID}/{potrosacID}")]
    public async Task<ActionResult> DodajPotrosnju(int edID, int potrosacID, [FromBody]Potrosnja potrosnja) {
        try {
            var ed = await Context.Elektrodistribucije.FindAsync(edID);
            var potrosac = await Context.Potrosaci.FindAsync(potrosacID);
            if (ed == null || potrosac == null)
                return NotFound("Nije pronadjen potrosac ili elektrodistro");
            potrosnja.Potrosac = potrosac;
            potrosnja.Elektrodistribucija = ed;
            await Context.Potrosnje.AddAsync(potrosnja);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata potrosnja sa id={potrosnja.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PronadjiPotrosaca/{brojBrojila}")]
    public async Task<ActionResult> PronadjiPotrosaca(string brojBrojila) {
        try {
            var potrosac = await Context.Potrosaci.Include(p => p.Potrosnje)
                                                  .Where(p => p.Potrosnje!.Any(q => q.BrojBrojila == brojBrojila))
                                                  .FirstOrDefaultAsync();
            return Ok(potrosac);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PronadjiPotrosace/{podrucjeID}/{datumOd}/{datumDo}")]
    public async Task<ActionResult> DodajElDistro(int podrucjeID, DateTime datumOd, DateTime datumDo) {
        try {
            var potrosaci = await Context.Potrosnje.Include(p => p.Potrosac)
                                                   .Include(p => p.Elektrodistribucija)
                                                   .Where(p => p.DatumUgovora >= datumOd && p.DatumUgovora <= datumDo
                                                            && p.Elektrodistribucija!.ID == podrucjeID
                                                   )
                                                   .Select(p => p.Potrosac)
                                                   .ToListAsync();
            return Ok(potrosaci);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

}
