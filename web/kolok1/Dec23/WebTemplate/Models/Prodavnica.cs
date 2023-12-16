namespace WebTemplate.Models;

public class Prodavnica {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public required string Lokacija { get; set; }

    public required string BrojTelefona { get; set; }

    public List<Popis>? Popisi { get; set; }
}