namespace WebTemplate.Models;

public class Grad {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public required string Lokacija { get; set; }

    public uint BrojKoloseka { get; set; }
    
    public uint BrojStanovnika { get; set; }

    public List<Relacija>? PolazneRelacije { get; set; }

    public List<Relacija>? DolazneRelacije { get; set; }
}