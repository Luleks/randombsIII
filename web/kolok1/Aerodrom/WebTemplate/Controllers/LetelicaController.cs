namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class LetelicaController : ControllerBase
{
    public Context Context { get; set; }

    public LetelicaController(Context context)
    {
        Context = context;
    }

    [HttpPost("DodajLetelicu")]
    public async Task<ActionResult> DodajLetelicu([FromBody]Letelica letelica) {
        try {
            await Context.Letelice.AddAsync(letelica);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata letelica sa id={letelica.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
    
}
