﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using WebTemplate.Models;

#nullable disable

namespace WebTemplate.Migrations
{
    [DbContext(typeof(Context))]
    partial class ContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "8.0.0")
                .HasAnnotation("Relational:MaxIdentifierLength", 128);

            SqlServerModelBuilderExtensions.UseIdentityColumns(modelBuilder);

            modelBuilder.Entity("WebTemplate.Models.Aerodrom", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<long>("KapacitetLetelica")
                        .HasColumnType("bigint");

                    b.Property<long>("KapacitetPutnika")
                        .HasColumnType("bigint");

                    b.Property<string>("Kod")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<double>("Latitude")
                        .HasColumnType("float");

                    b.Property<double>("Longitude")
                        .HasColumnType("float");

                    b.Property<string>("Naziv")
                        .IsRequired()
                        .HasMaxLength(100)
                        .HasColumnType("nvarchar(100)");

                    b.HasKey("ID");

                    b.ToTable("Aerodromi");
                });

            modelBuilder.Entity("WebTemplate.Models.Let", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<int?>("AerodromPoletanjaID")
                        .HasColumnType("int");

                    b.Property<int?>("AerodromSletanjaID")
                        .HasColumnType("int");

                    b.Property<long>("BrojPutnika")
                        .HasColumnType("bigint");

                    b.Property<int?>("LetelicaID")
                        .HasColumnType("int");

                    b.Property<DateTime>("VremePoletanja")
                        .HasColumnType("datetime2");

                    b.Property<DateTime>("VremeSletanja")
                        .HasColumnType("datetime2");

                    b.HasKey("ID");

                    b.HasIndex("AerodromPoletanjaID");

                    b.HasIndex("AerodromSletanjaID");

                    b.HasIndex("LetelicaID");

                    b.ToTable("Letovi");
                });

            modelBuilder.Entity("WebTemplate.Models.Letelica", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<long>("BrojMotora")
                        .HasColumnType("bigint");

                    b.Property<long>("KapacitetPutnika")
                        .HasColumnType("bigint");

                    b.Property<string>("Naziv")
                        .IsRequired()
                        .HasMaxLength(50)
                        .HasColumnType("nvarchar(50)");

                    b.Property<long>("Posada")
                        .HasColumnType("bigint");

                    b.HasKey("ID");

                    b.ToTable("Letelice");
                });

            modelBuilder.Entity("WebTemplate.Models.Let", b =>
                {
                    b.HasOne("WebTemplate.Models.Aerodrom", "AerodromPoletanja")
                        .WithMany("PoleteliLetovi")
                        .HasForeignKey("AerodromPoletanjaID");

                    b.HasOne("WebTemplate.Models.Aerodrom", "AerodromSletanja")
                        .WithMany("SleteliLetovi")
                        .HasForeignKey("AerodromSletanjaID");

                    b.HasOne("WebTemplate.Models.Letelica", "Letelica")
                        .WithMany("Letovi")
                        .HasForeignKey("LetelicaID");

                    b.Navigation("AerodromPoletanja");

                    b.Navigation("AerodromSletanja");

                    b.Navigation("Letelica");
                });

            modelBuilder.Entity("WebTemplate.Models.Aerodrom", b =>
                {
                    b.Navigation("PoleteliLetovi");

                    b.Navigation("SleteliLetovi");
                });

            modelBuilder.Entity("WebTemplate.Models.Letelica", b =>
                {
                    b.Navigation("Letovi");
                });
#pragma warning restore 612, 618
        }
    }
}
