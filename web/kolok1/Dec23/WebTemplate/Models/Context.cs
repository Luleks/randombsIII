namespace WebTemplate.Models;

public class Context : DbContext
{
    public required DbSet<Prodavnica> Prodavnice { get; set; }

    public required DbSet<Proizvod> Proizvodi { get; set; }

    public required DbSet<Popis> Popisi { get; set; }

    public Context(DbContextOptions options) : base(options)
    {
        
    }
}
