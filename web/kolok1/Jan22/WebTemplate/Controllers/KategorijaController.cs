namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class KategorijaController : ControllerBase
{
    public Context Context { get; set; }

    public KategorijaController(Context context)
    {
        Context = context;
    }

    [HttpGet("PreuzmiKategorije/{prodKucaID}")]
    public async Task<ActionResult> PreuzmiKategorije(int prodKucaID) {
        try {
            var kategorije = await Context.Kategorije.Include(p => p.ProdukcijskaKuca)
                                                     .Where(p => p.ProdukcijskaKuca!.ID == prodKucaID)
                                                     .Select(p => new {
                                                        p.ID,
                                                        p.Naziv
                                                     })
                                                     .ToListAsync();
            return Ok(kategorije);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajKategoriju/{prodKucaID}")]
    public async Task<ActionResult> DodajKategoriju(int prodKucaID, [FromBody]Kategorija kat) {
        try {
            var prodKuca = await Context.ProdukcijskeKuce.FindAsync(prodKucaID);
            if (prodKuca == null)
                return NotFound("Nije pronadjena prod kuca sa zadatim IDjem");
            kat.ProdukcijskaKuca = prodKuca;
            await Context.Kategorije.AddAsync(kat);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata kategorija sa id={kat.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
}