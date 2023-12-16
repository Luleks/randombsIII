namespace WebTemplate.Models;

public class Biljka {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public string? Slika { get; set; }

    public List<Vidjenje>? Vidjenja { get; set; }

    public List<Osobina>? Osobine { get; set; }
}