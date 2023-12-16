namespace WebTemplate.Models;

public class Numera {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public double Duzina { get; set; }

    public required string Zanr { get; set; }

    public uint BrUmetnika { get; set; }

    public Album? Album { get; set; }
}