namespace WebTemplate.Models;

public class Vlasnik {
    [Key]
    public int ID { get; set; }

    public required string Ime { get; set; }

    public required string Prezime { get; set; }

    public required DateTime DatumRodjenja { get; set; }

    public required string MestoRodjenja { get; set; }

    public List<Posedstvo>? Posedstva { get; set; }
}