namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class PodrucjeController : ControllerBase
{
    public Context Context { get; set; }

    public PodrucjeController(Context context)
    {
        Context = context;
    }

    [HttpGet("PreuzmiPodrucja")]
    public async Task<ActionResult> PreuzmiPodrucja() {
        try {
            var podrucja = await Context.Podrucja.Select(p => new {
                p.ID,
                p.Naziv
            }).ToListAsync();
            return Ok(podrucja);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajPodrucje")]
    public async Task<ActionResult> DodajPodrucje([FromBody]Podrucje podrucje) {
        try {
            await Context.Podrucja.AddAsync(podrucje);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodato podrucje sa ID={podrucje.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
    
    
}
