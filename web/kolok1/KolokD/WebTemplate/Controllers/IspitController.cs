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
    
    [HttpPost("DodajBanku")]
    public async Task<ActionResult> DodajBanku([FromBody]Banka banka) {
        try {
            await Context.Banke.AddAsync(banka);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata banka sa ID={banka.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajKlijenta")]
    public async Task<ActionResult> DodajKlijenta([FromBody]Klijent klijent) {
        try {
            await Context.Klijenti.AddAsync(klijent);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata banka sa ID={klijent.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajRacun/{klijentID}/{bankaID}")]
    public async Task<ActionResult> DodajRacun(int bankaID, int klijentID, [FromBody]Racun racun) {
        try {
            var klijent = await Context.Klijenti.FindAsync(klijentID);
            var banka = await Context.Banke.FindAsync(bankaID);
            if (klijent == null || banka == null)
                return NotFound("Nije pronadjen klijent ili banka");
            racun.Klijent = klijent;
            racun.Banka = banka;
            await Context.Racuni.AddAsync(racun);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat racun sa id={racun.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPut("IzmenaStanaj/{racunID}/{kolicina}")]
    public async Task<ActionResult> IzmeniStanje(int racunID, int kolicina) {
        try {
            var racun = await Context.Racuni.FindAsync(racunID);
            if (racun == null)
                return NotFound("Nije pronadjejn racun sa prosledjenim IDjem");
            if (racun.Kesh > kolicina)
                racun.PodignutKesh += (uint)(racun.Kesh - kolicina);
            racun.Kesh = kolicina;
            return Ok("Promenjeno stanje");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PreuzmiStatus/{bankaID}")]
    public async Task<ActionResult> PreuzmiStatus(int bankaID) {
        try {
            var pare = await Context.Racuni.Include(p => p.Banka)
                                           .Where(p => p.Banka!.ID == bankaID)
                                           .SumAsync(p => p.PodignutKesh + p.Kesh);
            return Ok(pare);
        }   
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
}
