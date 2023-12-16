namespace WebTemplate.Models;


public class Osobina {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public required string Vrednost { get; set; }

    public List<Biljka>? Biljke { get; set; }

    public List<NepoznataBiljka>? NepoznateBiljke { get; set; }
}