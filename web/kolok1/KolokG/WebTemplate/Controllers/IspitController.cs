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

    [HttpPost("DodajNekretninu")]
    public async Task<ActionResult> DodajNekretninu([FromBody]Nekretnina nekretnina) {
        try {
            await Context.Nekretnine.AddAsync(nekretnina);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata nekretnina sa id={nekretnina.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajVlasnika")]
    public async Task<ActionResult> DodajVlasnika([FromBody]Vlasnik vlasnik) {
        try {
            await Context.Vlasnici.AddAsync(vlasnik);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat vlasnik sa id={vlasnik.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajPosedstvo/{nekretninaID}/{vlasnikID}")]
    public async Task<ActionResult> DodajPosedstvo(int nekretninaID, int vlasnikID, [FromBody]Posedstvo posedstvo) {
        try {
            var nekretnina = await Context.Nekretnine.FindAsync(nekretninaID);
            var vlasnik = await Context.Vlasnici.FindAsync(vlasnikID);
            var poseduje = await Context.Posedstva.Include(p => p.Vlasnik)
                                                  .Include(p => p.Nekretnina)
                                                  .Where(p => p.Vlasnik!.ID == vlasnikID && p.Nekretnina!.ID == nekretninaID)
                                                  .FirstOrDefaultAsync();
            if (nekretnina == null || vlasnik == null)
                return NotFound("Ne postoji nekretnina i/ili vlasnik sa prosledjenim idjem");
            if (poseduje != null)
                return StatusCode(StatusCodes.Status403Forbidden, "Isti vlasnik ne moz da kupi kucu");
            nekretnina.BrPrethodnihVlasnika += 1;
            posedstvo.Nekretnina = nekretnina;
            posedstvo.Vlasnik = vlasnik;
            await Context.Posedstva.AddAsync(posedstvo);
            await Context.SaveChangesAsync();
            return Ok("Uspesno dodato posdstvo");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PreuzmiNekretnine/{vlasnikID}")]
    public async Task<ActionResult> PreuzmiNekretnine(int vlasnikID) {
        try {
            var nekretnine = await Context.Posedstva.Include(p => p.Nekretnina)
                                                    .Include(p => p.Vlasnik)
                                                    .Where(p => p.Vlasnik!.ID == vlasnikID)
                                                    .Select(p => p.Nekretnina!)
                                                    .ToListAsync();
            return Ok(nekretnine);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("ProsecnaCenaNekretnine/{nekretninaID}")]
    public async Task<ActionResult> ProsecnaCenaNekretnine(int nekretninaID) {
        try {
            var prosecna = await Context.Posedstva.Include(p => p.Nekretnina)
                                              .Where(p => p.Nekretnina!.ID == nekretninaID)
                                              .AverageAsync(p => p.VrednostNekretnine);
            return Ok(prosecna);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
    
}
