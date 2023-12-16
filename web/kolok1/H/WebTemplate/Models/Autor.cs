namespace WebTemplate.Models;

public class Autor {
    [Key]
    public int ID { get; set; }

    public required string Ime { get; set; }

    public required string Prezime { get; set; }

    public DateTime DatumRodjenja { get; set; }

    public List<Album>? Albumi { get; set; }

    public uint PrviAlbum { get; set; }
}