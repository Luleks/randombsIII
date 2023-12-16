namespace WebTemplate.Models;

public class Potrosnja {
    [Key]
    public int ID { get; set; }

    public uint KorisnickiBroj { get; set; }

    public DateTime DatumUgovora { get; set; }

    public required string BrojBrojila { get; set; }

    public Elektrodistribucija? Elektrodistribucija { get; set; }

    public Potrosac? Potrosac { get; set; }
}