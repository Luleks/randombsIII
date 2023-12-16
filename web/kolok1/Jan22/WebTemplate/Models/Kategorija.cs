using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class Kategorija {
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    [JsonIgnore]
    public ProdukcijskaKuca? ProdukcijskaKuca { get; set; }

    [JsonIgnore]
    public List<Film>? Filmovi { get; set; }
}