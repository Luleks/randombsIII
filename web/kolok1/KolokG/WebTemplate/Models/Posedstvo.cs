namespace WebTemplate.Models;

public class Posedstvo {
    [Key]
    public int ID { get; set; }

    public DateTime DatumKupovine { get; set; }

    public required string BrojUgovora { get; set; }

    public uint VrednostNekretnine { get; set; }

    public Vlasnik? Vlasnik { get; set; }

    public Nekretnina? Nekretnina { get; set; }
}