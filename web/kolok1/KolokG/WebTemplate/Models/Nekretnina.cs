namespace WebTemplate.Models;

public class Nekretnina {
    [Key]
    public int ID { get; set; }

    public required string Tip { get; set; }

    public required string Lokacija { get; set; }

    public uint BrPrethodnihVlasnika { get; set; }

    public List<Posedstvo>? Posedstva { get; set; }
}