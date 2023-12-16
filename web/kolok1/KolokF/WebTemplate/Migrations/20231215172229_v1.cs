using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class v1 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Kuvari",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Ime = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Prezime = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    DatumRodjenja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    StrucnaSprema = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Kuvari", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Restorani",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    MaxGosti = table.Column<long>(type: "bigint", nullable: false),
                    MaxKuvari = table.Column<long>(type: "bigint", nullable: false),
                    BrojTelefona = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Restorani", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Zaposljenja",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    DatumZaposlenja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Plata = table.Column<long>(type: "bigint", nullable: false),
                    Pozicija = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    RestoranID = table.Column<int>(type: "int", nullable: true),
                    KuvarID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Zaposljenja", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Zaposljenja_Kuvari_KuvarID",
                        column: x => x.KuvarID,
                        principalTable: "Kuvari",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Zaposljenja_Restorani_RestoranID",
                        column: x => x.RestoranID,
                        principalTable: "Restorani",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Zaposljenja_KuvarID",
                table: "Zaposljenja",
                column: "KuvarID");

            migrationBuilder.CreateIndex(
                name: "IX_Zaposljenja_RestoranID",
                table: "Zaposljenja",
                column: "RestoranID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Zaposljenja");

            migrationBuilder.DropTable(
                name: "Kuvari");

            migrationBuilder.DropTable(
                name: "Restorani");
        }
    }
}
