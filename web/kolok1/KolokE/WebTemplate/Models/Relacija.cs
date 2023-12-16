namespace WebTemplate.Models;

public class Relacija {
    [Key]
    public int ID { get; set; }

    public uint BrPutnika { get; set; }

    public double CenaKarte { get; set; }

    public DateTime Datum { get; set; }

    public Voz? Voz { get; set; }

    [InverseProperty("PolazneRelacije")]
    public Grad? PolazniGrad { get; set; }

    [InverseProperty("DolazneRelacije")]
    public Grad? DolazniGrad { get; set; }
}