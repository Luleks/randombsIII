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

    [HttpPost("DodajBolnicu")]
    public async Task<ActionResult> DodajBolnicu([FromBody]Bolnica bolnica) {
        try {
            await Context.Bolnice.AddAsync(bolnica);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata bolnica sa id={bolnica.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajLekara")]
    public async Task<ActionResult> DodajBolnicu([FromBody]Lekar lekar) {
        try {
            await Context.Lekari.AddAsync(lekar);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat lekar sa id={lekar.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodeliBolnicuLekaru/{bolnicaID}/lekarID")]
    public async Task<ActionResult> ZaposliLekara(int bolnicaID, int lekarID, [FromBody]Zaposleni zaposleni) {
        try {
            var bolnica = await Context.Bolnice.FindAsync(bolnicaID);
            var lekar = await Context.Lekari.FindAsync(lekarID);
            if (bolnica == null || lekar == null)
                return BadRequest("Nije pronadjenja bolnica ili lekar sa zadatim IDjem");
            zaposleni.Lekar = lekar;
            zaposleni.Bolnica = bolnica;
            await Context.Zaposleni.AddAsync(zaposleni);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodato zaposljenje sa id={zaposleni.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PronadjiLekare/{bolnicaID}")]
    public async Task<ActionResult> PronadjiLekare(int bolnicaID) {
        try {
            var lekari = await Context.Zaposleni.Include(p => p.Bolnica)
                                                .Include(p => p.Lekar)
                                                .Where(p => p.Bolnica!.ID == bolnicaID)
                                                .Select(p => new {
                                                    p.Lekar,
                                                    p.Specijalnost
                                                }).ToListAsync();
            return Ok(lekari);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("BolnicaImaPrevaranta/{bolnicaID}")]
    public async Task<ActionResult> ProveriBolnicu(int bolnicaID) {
        try {
            var lekariBezLicence = await Context.Zaposleni.Include(p => p.Bolnica)
                                                          .Include(p => p.Lekar)
                                                          .Where(p => p.Bolnica!.ID == bolnicaID)
                                                          .Where(p => p.Lekar!.DatumLicence == null)
                                                          .Select(p => new {
                                                            p.Lekar,
                                                            Licenca="NemaLicencu"
                                                          })
                                                          .ToListAsync();
            return Ok(lekariBezLicence);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
}
