namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    public required DbSet<Restoran> Restorani { get; set; }

    public required DbSet<Kuvar> Kuvari { get; set; }

    public required DbSet<Zaposleni> Zaposljenja { get; set; }

    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
