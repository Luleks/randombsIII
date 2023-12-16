namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class AerodromController : ControllerBase
{
    public Context Context { get; set; }

    public AerodromController(Context context)
    {
        Context = context;
    }
    
    [HttpPost("DodajAerodrom")]
    public async Task<ActionResult> DodajAerodrom([FromBody]Aerodrom aero) {
        try {
            await Context.Aerodromi.AddAsync(aero);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat aerodrom sa ID={aero.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
}
