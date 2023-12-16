namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class BiljkeController : ControllerBase
{
    public Context Context { get; set; }

    public BiljkeController(Context context)
    {
        Context = context;
    }

    [HttpPost("DodajNepronadjenu")]
    public async Task<ActionResult> DodajNepronadjenu([FromQuery]int[] osobine) {
        try {
            var nepoznata = new NepoznataBiljka {
                Osobine = new List<Osobina>()
            };
            bool uspelo = true;
            foreach (int o in osobine) {
                var osobina = await Context.Osobine.Include(p => p.NepoznateBiljke).Where(p => p.ID == o).FirstOrDefaultAsync();
                if (osobina == null) {
                    uspelo = false;
                    break;
                }
                if (osobina.NepoznateBiljke == null) 
                    osobina.NepoznateBiljke = new List<NepoznataBiljka>();
                osobina.NepoznateBiljke.Add(nepoznata);
                nepoznata.Osobine.Add(osobina);
            }
            if (uspelo) {
                await Context.NepoznateBiljke.AddAsync(nepoznata);
                await Context.SaveChangesAsync();
                return Ok($"Uspesno dodata nepoznata biljka sa ID={nepoznata.ID}");
            }   
            else {
                return NotFound("Neka od osobina nije pronadjena");
            }
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PreuzmiBiljke/{podrucjeID}")]
    public async Task<ActionResult> PreuzmiBiljke(int podrucjeID, [FromQuery]int[] osobine) {
        try {
            var biljke = await Context.Biljke.Include(p => p.Vidjenja!)
                                             .ThenInclude(q => q.Podrucje)
                                             .Include(p => p.Osobine)
                                             .Where(p => p.Vidjenja!.Any(q => q.Podrucje!.ID == podrucjeID))
                                             .Where(p => osobine.All(q => p.Osobine!.Any(r => r.ID == q)))
                                             .Select(p => new {
                                                p.ID,
                                                p.Naziv,
                                                BrojVidjenja=p.Vidjenja!.Count
                                             })   
                                             .ToListAsync();
            return Ok(biljke);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajVidjenje/{biljkaID}/{podrucjeID}")]
    public async Task<ActionResult> DodajPodrucje(int biljkaID, int podrucjeID, [FromBody]Vidjenje vidjenje) {
        try {
            var biljka = await Context.Biljke.Include(p => p.Vidjenja).Where(p => p.ID == biljkaID).FirstOrDefaultAsync();
            var podrucje = await Context.Podrucja.Include(p => p.Vidjenja).Where(p => p.ID == podrucjeID).FirstOrDefaultAsync();

            if (biljka == null || podrucje == null)
                return NotFound("Nije pronadjena biljka ili podrucje sa prosledjenim ID-jem");
            vidjenje.Biljka = biljka;
            vidjenje.Podrucje = podrucje;

            await Context.Vidjenja.AddAsync(vidjenje);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodato vidjenje sa ID={vidjenje.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajBiljku")]
    public async Task<ActionResult> DodajBiljku([FromBody]Biljka biljka, [FromQuery]int[] osobine) {
        try {
            bool upis = true;
            foreach (int o in osobine) {
                var osobina = await Context.Osobine.Include(p => p.Biljke).Where(p => p.ID == o).FirstOrDefaultAsync();
                if (osobina == null) {
                    upis = false;
                    break;
                }
                if (osobina.Biljke == null)
                    osobina.Biljke = new List<Biljka>();
                osobina.Biljke.Add(biljka);
                if (biljka.Osobine == null)
                    biljka.Osobine = new List<Osobina>();
                biljka.Osobine.Add(osobina);
            }
            if (upis) {
                await Context.Biljke.AddAsync(biljka);
                await Context.SaveChangesAsync();
                return Ok($"Uspesno dodata biljka sa id={biljka.ID}");
            }
            else {
                return NotFound("Neka od osobina nije pronadjena");
            }
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
}