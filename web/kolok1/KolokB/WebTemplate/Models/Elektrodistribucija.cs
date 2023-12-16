namespace WebTemplate.Models;

public class Elektrodistribucija {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public required string Grad { get; set; }

    public required string Gmail { get; set; }

    public uint BrojRadnika { get; set; }

    public List<Potrosnja>? Potrosnje { get; set; }
}