#See https://aka.ms/containerfastmode to understand how Visual Studio uses this Dockerfile to build your images for faster debugging.

FROM mcr.microsoft.com/dotnet/aspnet:6.0 AS base
WORKDIR /app
EXPOSE 80
EXPOSE 443

FROM mcr.microsoft.com/dotnet/sdk:6.0 AS build
WORKDIR /src
COPY ["ApPlant.Web.Api/ApPlant.Web.Api.csproj", "ApPlant.Web.Api/"]
RUN dotnet restore "ApPlant.Web.Api/ApPlant.Web.Api.csproj"
COPY . .
WORKDIR "/src/ApPlant.Web.Api"
RUN dotnet build "ApPlant.Web.Api.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "ApPlant.Web.Api.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "ApPlant.Web.Api.dll"]