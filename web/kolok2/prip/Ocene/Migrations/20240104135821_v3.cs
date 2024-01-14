using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Ocene.Migrations
{
    /// <inheritdoc />
    public partial class v3 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Ime",
                table: "Studenti");

            migrationBuilder.DropColumn(
                name: "Prezime",
                table: "Studenti");

            migrationBuilder.AddColumn<string>(
                name: "ImePrezime",
                table: "Studenti",
                type: "nvarchar(50)",
                maxLength: 50,
                nullable: true);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "ImePrezime",
                table: "Studenti");

            migrationBuilder.AddColumn<string>(
                name: "Ime",
                table: "Studenti",
                type: "nvarchar(max)",
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "Prezime",
                table: "Studenti",
                type: "nvarchar(max)",
                nullable: true);
        }
    }
}
