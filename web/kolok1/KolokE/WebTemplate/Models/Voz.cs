namespace WebTemplate.Models;

public class Voz {
    [Key]
    public int ID { get; set; }

    public uint KapcitetPutnika { get; set; }

    public DateTime DatumProizvodnje { get; set; }

    public double MaxBrzina { get; set; }

    public double Tezina { get; set; }

    public List<Relacija>? Relacije { get; set; }
}