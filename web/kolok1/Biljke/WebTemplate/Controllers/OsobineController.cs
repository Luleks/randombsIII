namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class OsobineController : ControllerBase
{
    public Context Context { get; set; }

    public OsobineController(Context context)
    {
        Context = context;
    }

    [HttpPost("DodajOsobinu")]
    public async Task<ActionResult> DodajOsobinu([FromBody]Osobina osobina) {
        try {
            await Context.Osobine.AddAsync(osobina);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata osobina sa id={osobina.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
}