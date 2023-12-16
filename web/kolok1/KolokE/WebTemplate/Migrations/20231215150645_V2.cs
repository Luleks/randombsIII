﻿using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class V2 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Gradovi",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Lokacija = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    BrojKoloseka = table.Column<long>(type: "bigint", nullable: false),
                    BrojStanovnika = table.Column<long>(type: "bigint", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Gradovi", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Vozovi",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    KapcitetPutnika = table.Column<long>(type: "bigint", nullable: false),
                    DatumProizvodnje = table.Column<DateTime>(type: "datetime2", nullable: false),
                    MaxBrzina = table.Column<double>(type: "float", nullable: false),
                    Tezina = table.Column<double>(type: "float", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Vozovi", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Relacije",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    BrPutnika = table.Column<long>(type: "bigint", nullable: false),
                    CenaKarte = table.Column<double>(type: "float", nullable: false),
                    Datum = table.Column<DateTime>(type: "datetime2", nullable: false),
                    VozID = table.Column<int>(type: "int", nullable: true),
                    PolazniGradID = table.Column<int>(type: "int", nullable: true),
                    DolazniGradID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Relacije", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Relacije_Gradovi_DolazniGradID",
                        column: x => x.DolazniGradID,
                        principalTable: "Gradovi",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Relacije_Gradovi_PolazniGradID",
                        column: x => x.PolazniGradID,
                        principalTable: "Gradovi",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Relacije_Vozovi_VozID",
                        column: x => x.VozID,
                        principalTable: "Vozovi",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Relacije_DolazniGradID",
                table: "Relacije",
                column: "DolazniGradID");

            migrationBuilder.CreateIndex(
                name: "IX_Relacije_PolazniGradID",
                table: "Relacije",
                column: "PolazniGradID");

            migrationBuilder.CreateIndex(
                name: "IX_Relacije_VozID",
                table: "Relacije",
                column: "VozID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Relacije");

            migrationBuilder.DropTable(
                name: "Gradovi");

            migrationBuilder.DropTable(
                name: "Vozovi");
        }
    }
}