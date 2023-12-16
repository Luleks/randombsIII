using Microsoft.AspNetCore.Http.HttpResults;

namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class IspitController : ControllerBase
{
    public IspitContext Context { get; set; }

    public IspitController(IspitContext context)
    {
        Context = context;
    }

    [HttpPost("DodajAutora")]
    public async Task<ActionResult> DodajAutora([FromBody]Autor autor) {
        try {
            await Context.Autori.AddAsync(autor);
            await Context.SaveChangesAsync();
            return Ok($"Dodat autor sa id={autor.ID}");
        } 
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajNumeru")]
    public async Task<ActionResult> DodajNumeru([FromBody]Numera numera) {
        try {
            await Context.Numere.AddAsync(numera);
            await Context.SaveChangesAsync();
            return Ok($"Dodat autor sa id={numera.ID}");
        } 
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpPost("DodajAlbum/{autorID}")]
    public async Task<ActionResult> DodajAlbum(int autorID, [FromQuery]int[] numere, [FromBody]Album album) {
        try {
            var autor = await Context.Autori.Include(p => p.Albumi).Where(p => p.ID == autorID).FirstOrDefaultAsync();
            if (autor == null)
                return NotFound("Nije pronadjen autor");
            album.Autor = autor;
            foreach (int n in numere) {
                var numera = await Context.Numere.Include(p => p.Album).Where(p => p.ID == n).FirstOrDefaultAsync();
                if (numera == null) {
                    return NotFound("Nije pronadjena numera");
                }
                numera.Album = album;
            }
            await Context.Albumi.AddAsync(album);
            await Context.SaveChangesAsync();

            var autorStari = await Context.Autori.Include(p => p.Albumi).Where(p => p.ID == autorID).FirstOrDefaultAsync();
            if (autorStari == null)
                return BadRequest("Error processing najstariji album");
            autorStari.PrviAlbum = autorStari.Albumi!.OrderBy(p => p.GodinaIzdavanja).Select(p => p.GodinaIzdavanja).FirstOrDefault();
            await Context.SaveChangesAsync();
            return Ok("Sve je proslo kako treba");
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpGet("Pretraga/{n}")]
    public async Task<ActionResult> Pretraga(uint n) {
        try {
            var autori = await Context.Autori.Where(p => (DateTime.Now.Year - p.PrviAlbum) > n).ToListAsync();
            return Ok(autori);
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

    [HttpDelete("ObrisiAlbum/{albumID}")]
    public async Task<ActionResult> ObrisiAlbum(int albumID) {
        try {
            var album = await Context.Albumi.Include(p => p.Autor).ThenInclude(q => q!.Albumi).Where(p => p.ID == albumID).FirstOrDefaultAsync();
            if (album == null)
                return NotFound("Album nije pronadjen");
            Context.Albumi.Remove(album);
            var prviAlbum = album.Autor!.Albumi!.OrderBy(p => p.GodinaIzdavanja).FirstOrDefault();
            if (prviAlbum == null)
                album.Autor!.PrviAlbum = 0;
            album.Autor!.PrviAlbum = prviAlbum!.GodinaIzdavanja;
            await Context.SaveChangesAsync();
            return Ok();
        }
        catch (Exception ec) {
            return BadRequest(ec.Message);
        }
    }

}
