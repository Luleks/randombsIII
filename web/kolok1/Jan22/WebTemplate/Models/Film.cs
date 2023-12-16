namespace WebTemplate.Models;

public class Film {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public List<double>? Ocene { get; set; }

    public Kategorija? Kategorija { get; set; }
}