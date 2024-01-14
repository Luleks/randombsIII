namespace WebTemplate.Models;

public class Popis {
    [Key]
    public int ID { get; set; }

    public uint DostupnaKolicina { get; set; }

    public double Cena { get; set; }

    public Prodavnica? Prodavnica { get; set; }

    public Proizvod? Proizvod { get; set; }
}