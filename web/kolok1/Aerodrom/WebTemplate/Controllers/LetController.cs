namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class LetController : ControllerBase
{
    public Context Context { get; set; }

    public LetController(Context context)
    {
        Context = context;
    }

    [HttpGet("Prosek/{aeroPoletaID}/{aeroSletaID}")]
    public async Task<ActionResult> ProsecnoVreme(int aeroPoletaID, int aeroSletaID) {
        try {
            var vreme = await Context.Letovi.Include(p => p.AerodromPoletanja)
                                            .Include(p => p.AerodromSletanja)
                                            .Where(p => p.AerodromPoletanja!.ID == aeroPoletaID && p.AerodromSletanja!.ID == aeroSletaID
                                                     || p.AerodromSletanja!.ID == aeroPoletaID && p.AerodromPoletanja!.ID == aeroSletaID)
                                            .Select(p => (p.VremeSletanja - p.VremePoletanja).TotalSeconds)
                                            .ToListAsync();
            if (vreme.Count == 0)
                return NotFound("Nema letova na ovoj trasi");
            var prosek = TimeSpan.FromSeconds(vreme.Average());
            return Ok(prosek);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PronadjiLetove/{aeroPoletanjaID}")]
    public async Task<ActionResult> PronadjiLetove(int aeroPoletanjaID) {
        try {
            var letovi = await Context.Letovi.Include(p => p.AerodromPoletanja)
                                             .Include(p => p.AerodromSletanja)
                                             .Include(p => p.Letelica)
                                             .Where(p => p.AerodromPoletanja!.ID == aeroPoletanjaID)
                                             .Select(p => new {
                                                letID=p.ID,
                                                vremePoletanja=p.VremePoletanja,
                                                vremeSletanja=p.VremeSletanja,
                                                brojPutnika=p.BrojPutnika,
                                                aeroPoletanja=p.AerodromPoletanja!.Naziv,
                                                aeroSletanja=p.AerodromSletanja!.Naziv,
                                                letelicaNaziv=p.Letelica!.Naziv
                                             })
                                             .ToListAsync();
            return Ok(letovi);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajLet/{aeroPoletanjaID}/{aeroSletanjaID}/{letelicaID}")]
    public async Task<ActionResult> DodajLet(int aeroPoletanjaID, int aeroSletanjaID, int letelicaID, [FromBody]Let let){
        try {
            var aeroPoletanja = await Context.Aerodromi.Include(p => p.PoleteliLetovi).Where(p => p.ID == aeroPoletanjaID).FirstOrDefaultAsync();
            var aeroSletanja = await Context.Aerodromi.Include(p => p.SleteliLetovi).Where(p =>p.ID == aeroSletanjaID).FirstOrDefaultAsync();
            var letelica = await Context.Letelice.Include(p => p.Letovi).Where(p => p.ID == letelicaID).FirstOrDefaultAsync();
            if (aeroPoletanja == null || aeroSletanja == null || letelica == null)
                return NotFound("AeroPoletanja/AeroSletanja/Letelica nije/nisu pronadjen(a)/pronadjeni");
            if (aeroPoletanja == aeroSletanja)
                return StatusCode(StatusCodes.Status403Forbidden, "aeroPolet == aeroSlet");
            if (let.VremePoletanja >= let.VremeSletanja)
                return StatusCode(StatusCodes.Status403Forbidden, "vremePolet >= vremeSlet");
            if (let.BrojPutnika > letelica.KapacitetPutnika)
                return StatusCode(StatusCodes.Status403Forbidden, "Previse putnika");
            let.AerodromPoletanja = aeroPoletanja;
            let.AerodromSletanja = aeroSletanja;
            let.Letelica = letelica;
            await Context.Letovi.AddAsync(let);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat let sa ID={letelica.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }    
}
