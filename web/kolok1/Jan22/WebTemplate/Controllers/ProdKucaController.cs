namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class ProdKucaController : ControllerBase
{
    public Context Context { get; set; }

    public ProdKucaController(Context context)
    {
        Context = context;
    }

    [HttpPost("DodajProdKucu")]
    public async Task<ActionResult> DodajProdKucu([FromBody]ProdukcijskaKuca prodKuca) {
        try {
            await Context.ProdukcijskeKuce.AddAsync(prodKuca);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata prod kuca sa id={prodKuca.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
    
}
