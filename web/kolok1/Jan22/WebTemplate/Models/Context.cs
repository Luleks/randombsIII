namespace WebTemplate.Models;

public class Context : DbContext
{
    public required DbSet<ProdukcijskaKuca> ProdukcijskeKuce { get; set; }
    public required DbSet<Kategorija> Kategorije { get; set; }
    public required DbSet<Film> Filmovi { get; set; }

    public Context(DbContextOptions options) : base(options)
    {
        
    }
}
