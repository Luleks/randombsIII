namespace WebTemplate.Models;

public class Racun {
    [Key]
    public int ID { get; set; }

    public int BrojRacuna { get; set; }

    public DateTime DatumOtvaranja { get; set; }

    public int Kesh { get; set; }

    public uint PodignutKesh { get; set; }

    public Klijent? Klijent { get; set; }

    public Banka? Banka { get; set; }
}