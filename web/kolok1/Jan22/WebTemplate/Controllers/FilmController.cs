namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class FilmController : ControllerBase
{
    public Context Context { get; set; }

    public FilmController(Context context)
    {
        Context = context;
    }

    [HttpGet("PreuzmiTri/{kategorijaID}")]
    public async Task<ActionResult> PreuzmiTri(int kategorijaID) {
        try {
            var flms = Context.Filmovi.Include(p => p.Kategorija)
                                            .Where(p => p.Kategorija!.ID == kategorijaID)
                                            .Where(p => p.Ocene != null)
                                            .OrderBy(p => p.Ocene!.Average());

            var res = new {
                najbolji=await flms.Select(p => new { p.Naziv, avg=p.Ocene!.Average() }).FirstOrDefaultAsync(),
                najgori=await flms.Select(p => new { p.Naziv, avg=p.Ocene!.Average() }).LastOrDefaultAsync(),
                srednji=await flms.Select(p => new { p.Naziv, avg=p.Ocene!.Average() }).Skip(flms.Count() / 2).FirstOrDefaultAsync()
            };
            return Ok(res);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("PreuzmiFilmove/{kategorijaID}")]
    public async Task<ActionResult> PreuzmiFilmove(int kategorijaID) {
        try {
            var flms = await Context.Filmovi.Include(p => p.Kategorija)
                                            .Where(p => p.Kategorija!.ID == kategorijaID)
                                            .Select(p => new {
                                                p.ID,
                                                p.Naziv,
                                                prosecnaOcena=p.Ocene!.Average()
                                            }).ToListAsync();
            return Ok(flms);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajOcenu/{filmID}/{ocena}")]
    public async Task<ActionResult> DodajOcenu(int filmID, double ocena) {
        try {
            var flm = await Context.Filmovi.Where(p => p.ID == filmID).FirstOrDefaultAsync();
            if (flm == null)
                return NotFound("Nije pronadjen film sa zadatim ID-jem");
            if (flm.Ocene == null)
                flm.Ocene = new List<double>();
            flm.Ocene.Add(ocena);
            await Context.SaveChangesAsync();
            return Ok("Ocena je uspesno pribelezena");
        }   
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajFilm/{kategorijaID}")]
    public async Task<ActionResult> DodajFilm(int kategorijaID, [FromBody]Film film) {
        try {
            var kat = await Context.Kategorije.FindAsync(kategorijaID);
            if (kat == null)
                return NotFound("Nije pronadjena kategorija");
            film.Kategorija = kat;
            film.Ocene = new List<double>();
            await Context.Filmovi.AddAsync(film);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat film sa id={film.ID}");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }
}