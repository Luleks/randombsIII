namespace WebTemplate.Models;

public class Proizvod {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public required string Kategorija { get; set; }

    public List<Popis>? Popisi { get; set; }

}