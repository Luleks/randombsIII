using System.Collections.Frozen;

namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class ProizvodController : ControllerBase
{
    public Context Context { get; set; }

    public HashSet<string> Kategorije { get; set; }

    public ProizvodController(Context context)
    {
        Context = context;
        Kategorije = new HashSet<string>() { "Knjiga", "Igracka", "Pribor", "Ostalo" };
    }

    [HttpPut("ProdajProizvod/{popisID}/{kolicina}")]
    public async Task<ActionResult> ProdajProizvod(int popisID, uint kolicina) {
        try {
            var popis = await Context.Popisi.Include(p => p.Proizvod).Where(p => p.ID == popisID).FirstOrDefaultAsync();
            if (popis == null)
                return NotFound("Proizvod nije pronadjen");
            if (popis.DostupnaKolicina < kolicina)
                return StatusCode(StatusCodes.Status403Forbidden, "Nema dovoljnu in stock");
            popis.DostupnaKolicina -= kolicina;
            if (popis.DostupnaKolicina == 0) {
                Context.Popisi.Remove(popis);
                var proizvod = await Context.Proizvodi.FindAsync(popis.Proizvod!.ID);
                Context.Proizvodi.Remove(proizvod!);
            }
            await Context.SaveChangesAsync();
            return Ok("Proizvod uspesno prodat");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PreuzmiProizvode/{prodavnicaID}/{kategorija}")]
    public async Task<ActionResult> PreuzmiProizvode(int prodavnicaID, string kategorija) {
        try {
            var popisi = await Context.Popisi.Include(p => p.Prodavnica)
                                             .Include(p => p.Proizvod)
                                             .Where(p => p.Prodavnica!.ID == prodavnicaID)
                                             .Where(p => p.Proizvod!.Kategorija == kategorija)
                                             .Select(p => new {
                                                popisID=p.ID,
                                                proizvodNaziv=p.Proizvod!.Naziv,
                                                proizvodKolicina=p.DostupnaKolicina
                                             })
                                             .ToListAsync();
            return Ok(popisi);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PrivabiKategorije")]
    public ActionResult PreuzmiKategorije() {
        try {
            return Ok(Kategorije.ToList());
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajProizvod/{prodavnicaID}/{cena}/{kolicina}")]
    public async Task<ActionResult> DodajProizvod(int prodavnicaID, double cena, uint kolicina, [FromBody]Proizvod proizvod) {
        try {
            var prod = await Context.Prodavnice.Include(p => p.Popisi).Where(p => p.ID == prodavnicaID).FirstOrDefaultAsync();
            if (prod == null)
                return NotFound("Nije pronadjena prodavnica sa prosledjenim IDjem");
            if (prod.Popisi!.Count() >= 100)
                return StatusCode(StatusCodes.Status403Forbidden, "Prodavnica je puna");
            if (!Kategorije.Contains(proizvod.Kategorija))
                return StatusCode(StatusCodes.Status403Forbidden, "Nepostojeca kategorija");
            var popis = new Popis {
                DostupnaKolicina=kolicina,
                Cena=cena,
                Prodavnica=prod,
                Proizvod=proizvod
            };
            await Context.Popisi.AddAsync(popis);
            await Context.SaveChangesAsync();
            return Ok("Uspesno dodat proizvod u prodavnicu");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
    
}
