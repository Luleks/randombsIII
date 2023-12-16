using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class V1 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Nekretnine",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Tip = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Lokacija = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    BrPrethodnihVlasnika = table.Column<long>(type: "bigint", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Nekretnine", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Vlasnici",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Ime = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Prezime = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    DatumRodjenja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    MestoRodjenja = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Vlasnici", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Posedstva",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    DatumKupovine = table.Column<DateTime>(type: "datetime2", nullable: false),
                    BrojUgovora = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    VrednostNekretnine = table.Column<long>(type: "bigint", nullable: false),
                    VlasnikID = table.Column<int>(type: "int", nullable: true),
                    NekretninaID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Posedstva", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Posedstva_Nekretnine_NekretninaID",
                        column: x => x.NekretninaID,
                        principalTable: "Nekretnine",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Posedstva_Vlasnici_VlasnikID",
                        column: x => x.VlasnikID,
                        principalTable: "Vlasnici",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Posedstva_NekretninaID",
                table: "Posedstva",
                column: "NekretninaID");

            migrationBuilder.CreateIndex(
                name: "IX_Posedstva_VlasnikID",
                table: "Posedstva",
                column: "VlasnikID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Posedstva");

            migrationBuilder.DropTable(
                name: "Nekretnine");

            migrationBuilder.DropTable(
                name: "Vlasnici");
        }
    }
}
