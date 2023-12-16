namespace WebTemplate.Models;


public class Vidjenje {
    [Key]
    public int ID { get; set; }

    public Biljka? Biljka { get; set; }
    
    public Podrucje? Podrucje { get; set; }

    [Range(-180, 180)]
    public double Longitude { get; set; }

    [Range(-90, 90)]
    public double Latitude { get; set; }

    public DateTime DatumIVreme { get; set; }
}