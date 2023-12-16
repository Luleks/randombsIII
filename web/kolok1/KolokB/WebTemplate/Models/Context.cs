namespace WebTemplate.Models;

public class Context : DbContext
{
    public required DbSet<Potrosac> Potrosaci { get; set; }

    public required DbSet<Potrosnja> Potrosnje { get; set; }

    public required DbSet<Elektrodistribucija> Elektrodistribucije { get; set; }

    public Context(DbContextOptions options) : base(options)
    {
        
    }
}
