namespace WebTemplate.Models;

public class Context : DbContext
{
    public required DbSet<Aerodrom> Aerodromi { get; set; }

    public required DbSet<Let> Letovi { get; set; }

    public required DbSet<Letelica> Letelice { get; set; }

    public Context(DbContextOptions options) : base(options)
    {
        
    }
}
