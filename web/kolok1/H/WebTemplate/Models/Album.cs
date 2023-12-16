namespace WebTemplate.Models;

public class Album {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    [Range(typeof(int), "1900", "2023")]
    public uint GodinaIzdavanja { get; set; }

    public required string IzdavackaKuca { get; set; }

    public List<Numera>? Numere { get; set; }

    public Autor? Autor;
}