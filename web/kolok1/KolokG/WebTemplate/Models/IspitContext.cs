namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    public required DbSet<Nekretnina> Nekretnine { get; set; }

    public required DbSet<Vlasnik> Vlasnici { get; set; }

    public required DbSet<Posedstvo> Posedstva { get; set; }


    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
