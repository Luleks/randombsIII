namespace WebTemplate.Models;

public class Restoran {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public uint MaxGosti { get; set; }

    public uint MaxKuvari { get; set; }

    [RegularExpression(@"^(\+3816)([0-9])([0-9]){6,9}$")]
    public required string BrojTelefona { get; set; }

    public List<Zaposleni>? Zaposleni { get; set; }
}