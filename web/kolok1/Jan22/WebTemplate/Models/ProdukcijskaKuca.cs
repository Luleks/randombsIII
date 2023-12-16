namespace WebTemplate.Models;

public class ProdukcijskaKuca {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public List<Kategorija>? Kategorije { get; set; }
}