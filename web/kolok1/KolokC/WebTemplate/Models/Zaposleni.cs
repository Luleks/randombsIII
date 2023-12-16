namespace WebTemplate.Models;

public class Zaposleni {
    [Key]
    public int ID { get; set; }

    public required string IDBroj { get; set; }

    public DateTime DatumPotpisivanja { get; set; }

    public required string Specijalnost { get; set; }

    public Lekar? Lekar { get; set; }

    public Bolnica? Bolnica { get; set; }
}