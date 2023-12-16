namespace WebTemplate.Models;

public class Aerodrom {
    [Key]
    public int ID { get; set; }

    [MaxLength(100)]
    public required string Naziv { get; set; }

    [Length(3, 3)]
    public required string Kod { get; set; }

    [Range(-180, 180)]
    public double Longitude { get; set; }

    [Range(-90, 90)]
    public double Latitude { get; set; }

    public uint KapacitetLetelica { get; set; }
    public uint KapacitetPutnika { get; set; }

    public List<Let>? PoleteliLetovi { get; set; }

    public List<Let>? SleteliLetovi { get; set; }
}