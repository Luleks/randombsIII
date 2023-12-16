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
    
    [HttpPost("DodajRestoran")]
    public async Task<ActionResult> DodajRestoran([FromBody]Restoran restoran) {
        try {
            await Context.Restorani.AddAsync(restoran);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat restoran sa ID={restoran.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajKuvara")]
    public async Task<ActionResult> DodajKuvara([FromBody]Kuvar kuvar) {
        try {
            await Context.Kuvari.AddAsync(kuvar);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat restoran sa ID={kuvar.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajZaposlenog/{restoranID}/{kuvarID}")]
    public async Task<ActionResult> DodajZaposlenog(int restoranID, int kuvarID, [FromBody]Zaposleni zaposleni) {
        try {
            var restoran = await Context.Restorani.FindAsync(restoranID);
            var kuvar = await Context.Kuvari.FindAsync(kuvarID);
            var zaposlenje = await Context.Zaposljenja.Include(p => p.Restoran)
                                                      .Include(p => p.Kuvar)
                                                      .Where(p => p.Kuvar!.ID == kuvarID && p.Restoran!.ID == restoranID)
                                                      .FirstOrDefaultAsync();
            if (restoran == null || kuvar == null || zaposlenje != null)
                return NotFound("Nije pronadjen restoran ili kuvar ili je kuvar vec zaposlen u ovom restoranu");
            var zaposleniURest = await Context.Zaposljenja.Include(p => p.Restoran).Where(p => p.Restoran!.ID == restoranID).CountAsync();
            if (zaposleniURest >= restoran.MaxKuvari)
                return StatusCode(StatusCodes.Status403Forbidden, "Max kapacitet kufara");
            zaposleni.Restoran = restoran;
            zaposleni.Kuvar = kuvar;
            await Context.Zaposljenja.AddAsync(zaposleni);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno zaposlen kuvar sa id={zaposleni.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("UkupnaPlata/{kuvarID}")]
    public async Task<ActionResult> DodajRestoran(int kuvarID) {
        try {
            var placa = await Context.Zaposljenja.Include(p => p.Kuvar)
                                     .Where(p => p.Kuvar!.ID == kuvarID)
                                     .SumAsync(p => p.Plata);
            return Ok(placa);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("MostBiziKuvar")]
    public async Task<ActionResult> MostBiziKuvar() {
        try {
            var kuvar = await Context.Kuvari.Include(p => p.Poslovi)
                                            .OrderBy(p => p.Poslovi!.Count)
                                            .LastOrDefaultAsync();
            return Ok(kuvar);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
}
