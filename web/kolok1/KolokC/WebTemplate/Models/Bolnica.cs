namespace WebTemplate.Models;

public class Bolnica {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public required string Lokacija { get; set; }

    public uint BrojOdeljenja { get; set; }

    public uint Osoblje { get; set; }

    public required string BrojTelefona { get; set; }
    
    public List<Zaposleni>? Zaposleni { get; set; }
}