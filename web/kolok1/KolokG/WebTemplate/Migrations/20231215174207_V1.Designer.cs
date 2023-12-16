﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using WebTemplate.Models;

#nullable disable

namespace WebTemplate.Migrations
{
    [DbContext(typeof(IspitContext))]
    [Migration("20231215174207_V1")]
    partial class V1
    {
        /// <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "8.0.0")
                .HasAnnotation("Relational:MaxIdentifierLength", 128);

            SqlServerModelBuilderExtensions.UseIdentityColumns(modelBuilder);

            modelBuilder.Entity("WebTemplate.Models.Nekretnina", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<long>("BrPrethodnihVlasnika")
                        .HasColumnType("bigint");

                    b.Property<string>("Lokacija")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Tip")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("ID");

                    b.ToTable("Nekretnine");
                });

            modelBuilder.Entity("WebTemplate.Models.Posedstvo", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<string>("BrojUgovora")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<DateTime>("DatumKupovine")
                        .HasColumnType("datetime2");

                    b.Property<int?>("NekretninaID")
                        .HasColumnType("int");

                    b.Property<int?>("VlasnikID")
                        .HasColumnType("int");

                    b.Property<long>("VrednostNekretnine")
                        .HasColumnType("bigint");

                    b.HasKey("ID");

                    b.HasIndex("NekretninaID");

                    b.HasIndex("VlasnikID");

                    b.ToTable("Posedstva");
                });

            modelBuilder.Entity("WebTemplate.Models.Vlasnik", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<DateTime>("DatumRodjenja")
                        .HasColumnType("datetime2");

                    b.Property<string>("Ime")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("MestoRodjenja")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Prezime")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("ID");

                    b.ToTable("Vlasnici");
                });

            modelBuilder.Entity("WebTemplate.Models.Posedstvo", b =>
                {
                    b.HasOne("WebTemplate.Models.Nekretnina", "Nekretnina")
                        .WithMany("Posedstva")
                        .HasForeignKey("NekretninaID");

                    b.HasOne("WebTemplate.Models.Vlasnik", "Vlasnik")
                        .WithMany("Posedstva")
                        .HasForeignKey("VlasnikID");

                    b.Navigation("Nekretnina");

                    b.Navigation("Vlasnik");
                });

            modelBuilder.Entity("WebTemplate.Models.Nekretnina", b =>
                {
                    b.Navigation("Posedstva");
                });

            modelBuilder.Entity("WebTemplate.Models.Vlasnik", b =>
                {
                    b.Navigation("Posedstva");
                });
#pragma warning restore 612, 618
        }
    }
}