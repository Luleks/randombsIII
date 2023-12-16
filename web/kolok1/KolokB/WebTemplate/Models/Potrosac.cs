using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class Potrosac {
    [Key]
    public int ID { get; set; }

    public required string Ime { get; set; }

    public required string Prezime { get; set; }

    public uint GodinaRodjenja { get; set; }

    public required string MestoRodjenja { get; set; }

    [JsonIgnore]
    public List<Potrosnja>? Potrosnje { get; set; }
}