﻿using Microsoft.EntityFrameworkCore.Migrations;

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
                name: "ProdukcijskeKuce",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_ProdukcijskeKuce", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Kategorije",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    ProdukcijskaKucaID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Kategorije", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Kategorije_ProdukcijskeKuce_ProdukcijskaKucaID",
                        column: x => x.ProdukcijskaKucaID,
                        principalTable: "ProdukcijskeKuce",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "Filmovi",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Ocene = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    KategorijaID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Filmovi", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Filmovi_Kategorije_KategorijaID",
                        column: x => x.KategorijaID,
                        principalTable: "Kategorije",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Filmovi_KategorijaID",
                table: "Filmovi",
                column: "KategorijaID");

            migrationBuilder.CreateIndex(
                name: "IX_Kategorije_ProdukcijskaKucaID",
                table: "Kategorije",
                column: "ProdukcijskaKucaID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Filmovi");

            migrationBuilder.DropTable(
                name: "Kategorije");

            migrationBuilder.DropTable(
                name: "ProdukcijskeKuce");
        }
    }
}
