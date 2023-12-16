namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class ProdavnicaController : ControllerBase
{
    public Context Context { get; set; }

    public ProdavnicaController(Context context)
    {
        Context = context;
    }

    [HttpPost("DodajProdavnicu")]
    public async Task<ActionResult> DodajProdavnicu([FromBody]Prodavnica prodavnica) {
        try {
            await Context.Prodavnice.AddAsync(prodavnica);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata prodavnica sa ID={prodavnica.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
    
}
